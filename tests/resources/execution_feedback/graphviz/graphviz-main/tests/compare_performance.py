#!/usr/bin/env python3

"""
Compare the runtime performance of one or more versions of Graphviz.

When making changes to Graphviz’s code that may affect performance, you can
run this script to evaluate the effect of your changes.

Candidates are identified by the path to the corresponding `dot` program to run,
although tests involve other Graphviz programs as well (e.g., neato, circo, ccomps)

Example usage:
  python3 compare_performance.py \
    /path/to/install/before/bin/dot /path/to/install/after/bin/dot

This will run various known expensive workloads and report the relative performance of
the two or more versions you gave it as tabulated results.
"""

import argparse
import dataclasses
import io
import os
import platform
import shlex
import shutil
import subprocess
import sys
import time
from pathlib import Path
from typing import Union

import tabulate

MY_DIR = Path(__file__).resolve().parent
"""
path to our containing directory
"""


@dataclasses.dataclass
class Test:
    """a workload for profiling"""

    args: list[Union[str, Path]]
    expect_success: bool = True


TESTS: dict[str, Test] = {
    "#1172 1": Test(["dot", "-Ln3", "-Txdot", MY_DIR / "1172_1.xdot"]),  # ~45s
    "#1172 2": Test(["dot", "-Ln3", "-Txdot", MY_DIR / "1172_2.xdot"]),  # ~20s
    "#1652": Test(["neato", "-Tsvg", MY_DIR / "1652.dot"]),  # ~20s
    "#1718": Test(["circo", "-Tsvg", MY_DIR / "1718.dot"]),  # ~2m20s
    "#1864": Test(["neato", "-Tsvg", MY_DIR / "1864.dot"]),  # ~31m35s
    "#2064": Test(
        [
            "dot",
            "-Gnslimit=2",
            "-Gnslimit1=2",
            "-Gmaxiter=5000",
            "-Tsvg",
            MY_DIR / "2064.dot",
        ]
    ),  # ~7m30s
    "#2095": Test(["dot", "-Tsvg", MY_DIR / "2095_1.dot"]),  # ~1m15s
    "#2108": Test(["dot", "-Tsvg", MY_DIR / "2108.dot"]),  # ~30s
    "#2222": Test(["dot", "-Tsvg", MY_DIR / "2222.dot"]),  # ~40s
    "#2343": Test(["dot", "-Tpng", MY_DIR / "2343.dot"]),  # 1m50s
    "#2475 1": Test(
        [
            "dot",
            "-Gnslimit=2",
            "-Gnslimit1=2",
            "-Gmclimit=.33",
            "-Gremincross=false",
            "-Gsearchsize=20",
            "-Gsplines=false",
            "-Tsvg",
            MY_DIR / "2475_1.dot",
        ]
    ),  # ~55m00s
    "#2475 2": Test(
        [
            "dot",
            "-Gnslimit=2",
            "-Gnslimit1=2",
            "-Gmclimit=.33",
            "-Gremincross=false",
            "-Gsearchsize=20",
            "-Gsplines=false",
            "-Tsvg",
            MY_DIR / "2475_2.dot",
        ]
    ),  # ~10s
    "#2593": Test(["ccomps", MY_DIR / "2593.dot"], False),  # ~2s
    "#2621": Test(["dot", "-Tpng", MY_DIR / "2621.dot"]),  # ~12m00s
    "#2646": Test(["dot", "-Tpdf", MY_DIR / "2646.dot"]),  # ~5m30s
    # "#2834 1": Test(["dot", "-Tpng", MY_DIR / "2834.dot"]),  # ~12h45m
    "#2834 2": Test(["dot", "-Gphase=2", MY_DIR / "2834.dot"]),  # ~1m45s
    "!2854": Test(["dot", "-Tsvg", MY_DIR / "2854.dot"]),  # ~7m40s
}
"""
relevant workloads to evaluate

Entries are a test name mapped to a command to run. Commands will all have an
implicit `-o /dev/null` added to them when executed.
"""


def run(test: Test, root: Union[str, Path]):
    """
    run a command, pre-echoing it like Bash’s `set -x`

    Args:
        test: Workload to run
        root: Root directory of the Graphviz installation under test
    """
    assert len(test.args) > 0

    exe = root / "bin"
    lib = root / "lib"

    env = os.environ.copy()
    if platform.system() == "Darwin":
        if "DYLD_LIBRARY_PATH" in env:
            env["DYLD_LIBRARY_PATH"] = f"{lib}{os.pathsep}{env['DYLD_LIBRARY_PATH']}"
            prefix = f'DYLD_LIBRARY_PATH="{lib}{os.pathsep}${{DYLD_LIBRARY_PATH}}"'
        else:
            env["DYLD_LIBRARY_PATH"] = str(lib)
            prefix = f'DYLD_LIBRARY_PATH="{lib}"'
    else:
        if "LD_LIBRARY_PATH" in env:
            env["LD_LIBRARY_PATH"] = f"{lib}{os.pathsep}{env['LD_LIBRARY_PATH']}"
            prefix = f'LD_LIBRARY_PATH="{lib}{os.pathsep}${{LD_LIBRARY_PATH}}"'
        else:
            env["LD_LIBRARY_PATH"] = str(lib)
            prefix = f'LD_LIBRARY_PATH="{lib}"'

    arg0 = shutil.which(test.args[0], path=exe)
    assert arg0 is not None, "{test.args[0]} not found in installation {root}"
    argv = [arg0] + test.args[1:] + ["-o", os.devnull]

    print(f"+ env {prefix} {shlex.join(str(x) for x in argv)}", flush=True)
    subprocess.run(argv, check=test.expect_success)


def pretty_time(duration: float):
    """turn a count of seconds into XXhXXmXXs"""
    hours = int(duration / 60 / 60)
    minutes = int(duration / 60 % 60)
    seconds = int(duration % 60)
    return f"{hours}h{minutes:02}m{seconds:02}s"


def main(args: list[str]) -> int:
    """entry point"""

    # parse command line options
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument(
        "candidate",
        type=argparse.FileType("rb"),
        nargs="+",
        help="Graphviz binaries to compare",
    )
    options = parser.parse_args(args[1:])

    # derive installation roots
    roots = []
    for dot in options.candidate:
        exe = Path(dot.name).resolve()
        roots += [exe.parents[1]]
    headers = ["test case", "program"] + roots

    print(f"Comparing {[str(r) for r in roots]}…", flush=True)

    results: list[list[str]] = []
    for name, test in TESTS.items():
        result = []
        for root in roots:
            start = time.monotonic()
            run(test, root)
            stop = time.monotonic()
            result += [stop - start]

            # dump results progress, so that if the user interrupts they still have
            # something partial to analyze
            row = [name, test.args[0]]

            for index, r in enumerate(result):
                cell = io.StringIO()
                if index != 0:
                    if r < result[0]:
                        cell.write("\033[32m")  # green
                    elif r > result[0]:
                        cell.write("\033[31m")  # red
                cell.write(pretty_time(r))
                if index != 0:
                    cell.write(f" ({int((r - result[0]) / result[0]  * 100)}%)\033[0m")
                row += [cell.getvalue()]
            print(
                tabulate.tabulate(
                    results + [row], headers=headers, tablefmt="simple_outline"
                ),
                flush=True,
            )
        results += [row]

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
