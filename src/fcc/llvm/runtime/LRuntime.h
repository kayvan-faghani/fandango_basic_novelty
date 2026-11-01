#ifndef LRUNTIME_H
#define LRUNTIME_H

#ifdef __cplusplus
#include <cstdint>


extern "C" {
#else
#include <stdint.h>
#endif

void _runtime_print(char* s);
void _runtime_branch(uint32_t branchid);
void _runtime_bb(char* moduleIdentifier, uint32_t bbid);
void _runtime_output();
void _runtime_initialize(char* moduleIdentifier, uint64_t* module_bb_hitcount_array, uint32_t size);
void _runtime_track_heap_alloc(uint32_t bytes);

void _runtime_start_logging();
void _runtime_stop_logging();


#ifdef __cplusplus
}
#endif

#endif
