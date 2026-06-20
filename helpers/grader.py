import builtins
import glob
import os
import runpy
import sys

# ──────────────────────────────────
# Echo input() like the old grader
# ──────────────────────────────────
_original_input = builtins.input


def input(prompt: str = "") -> str:
    print(prompt, end="")
    user = _original_input()
    print(user)
    return user


builtins.input = input  # override globally


# ──────────────────────────────────
# Pick the student script
# ──────────────────────────────────
def find_student_script() -> str:
    """Return a reasonable default *.py to run."""
    candidates = [
        f
        for f in glob.glob("*.py")
        if os.path.basename(f) not in {"grader.py", "__init__.py"}
    ]
    if not candidates:
        sys.exit("❌  No *.py candidate found in repository root.")

    if len(candidates) == 1:
        return candidates[0]

    # Prefer a file that has a __main__ guard
    for fname in candidates:
        try:
            with open(fname, "r", encoding="utf-8") as fh:
                if "__main__" in fh.read():
                    return fname
        except OSError:
            pass

    # Fallback: alphabetical first
    return sorted(candidates)[0]


# Priority: CLI arg → env var → heuristic
script = (
    sys.argv[1]
    if len(sys.argv) > 1
    else os.getenv("STUDENT_SCRIPT", find_student_script())
)

runpy.run_path(script, run_name="__main__")
