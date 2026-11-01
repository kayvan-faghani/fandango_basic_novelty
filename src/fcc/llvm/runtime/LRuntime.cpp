#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <memory>
#include <cassert>
#include <unordered_map>

#include "LRuntime.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

bool in_json_code = false; // json (nlohmann) code may call libc++, which is instrumented. We don't want to log BBs/LOADs from that though.
bool logging = false;
uint8_t* input_buffer = nullptr;
size_t size_input_buffer = 0;
uint32_t cur_bb;
uint64_t allocated_bytes = 0; // for malloc allocation tracking

struct ModuleBBTable {
    uint64_t* module_bb_hitcount_array;
    uint32_t size;

    bool operator==(const ModuleBBTable& other) const {
        return module_bb_hitcount_array == other.module_bb_hitcount_array && size == other.size;
    }
};

std::unordered_map<std::string, ModuleBBTable> module_bb_hitcount_map;

// #define DEBUG_PRINTS
#ifdef DEBUG_PRINTS
template <typename... Args>
inline void debug_print(Args&&... args) {
    std::ostringstream oss;
    (oss << ... << std::forward<Args>(args)); // Fold expression to stream all arguments
    std::cerr << oss.str() << std::endl;
}
#else
template <typename... Args>
inline void debug_print(Args&&...) {}
#endif


void atexit_callback() {
    debug_print("atexit_callback()");
    _runtime_output();
}

bool initialized = false;
void _runtime_initialize(char* moduleIdentifier, uint64_t* module_bb_hitcount_array, uint32_t size) {
    if (module_bb_hitcount_map.find(moduleIdentifier) != module_bb_hitcount_map.end()) {
        debug_print("Module already found: ", moduleIdentifier);
        assert(false && "Module already found");
        return;
    }

    module_bb_hitcount_map[moduleIdentifier] = ModuleBBTable{module_bb_hitcount_array, size};

    // _runtime_initialize is added to ctor of each module
    // after linking, the final module will call _runtime_initialize X times
    // we only want to register one atexit() hook though, hence bailing out here.
    if (initialized) return;
    initialized = true;
    
    // If logging is desired only at a later point in the program, the user shall add a call to
    // _runtime_stop_logging at the program entry point, and a _runtime_start_logging at the
    // respective position.
    _runtime_start_logging();
    atexit(atexit_callback);

    debug_print("_runtime_initialize()");
}

void _runtime_track_heap_alloc(uint32_t bytes) {
    allocated_bytes += bytes;
    debug_print("_runtime_track_heap_alloc: ", bytes, " allocated_bytes: ", allocated_bytes);
}

void _runtime_print(char* s) {
    if (in_json_code || !logging) return;

    debug_print("Runtime: ", s);
}

void _runtime_bb(char* moduleIdentifier, uint32_t bbid) {
    if (moduleIdentifier || bbid) {} // unused
}

void _runtime_branch(uint32_t branchid) {
    if (in_json_code || !logging) return;

    debug_print("_runtime_branch: ", branchid);
}

void _runtime_output() {
    std::cerr << "_runtime_output (serialize_trace) called\n";
    const char* execution_trace_json = std::getenv("EXECUTION_TRACE_JSON");
    if (execution_trace_json == NULL) {
        std::cerr << "Error: Execution trace output file must be provided via EXECUTION_TRACE_JSON environment variable.\n";
    } else {
        std::ofstream file(execution_trace_json);
        json j_output;
        j_output["trace"] = json::object();
        for (const auto& [module_identifier, module_bb_map] : module_bb_hitcount_map) {
            j_output["trace"][module_identifier] = json::object();
            for (uint32_t bbid = 0; bbid < module_bb_map.size; bbid++) {
                auto hitcount = module_bb_map.module_bb_hitcount_array[bbid];
                if (hitcount > 0) {
                    j_output["trace"][module_identifier][std::to_string(bbid)] = hitcount;
                }
            }
            if (j_output["trace"][module_identifier].empty()) {
                j_output["trace"].erase(module_identifier);
            }

        }
        j_output["allocated_bytes"] = allocated_bytes;
        file << j_output;
        file.close();
    }
}

void _runtime_start_logging() {
    logging = true;
}

void _runtime_stop_logging() {
    logging = false;
}