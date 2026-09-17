# ============================================================================
# Makefile -- SDPA Attention Lab for Raspberry Pi 4B
# ============================================================================
.PHONY: all clean gen_data check check_task1 check_task2 check_task3 check_task4 grade upper_bound

CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -O2 -march=armv8-a -Isrc
LDFLAGS  = -pthread -lm
PYTHON   = python3
PIP      = pip3
PYPI_MIRROR = https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple

# -- Framework sources (students do NOT edit these) --
FRAMEWORK_SRC = src/sdpa_utils.c src/main.c
FRAMEWORK_HDR = src/sdpa.h src/sdpa_utils.h src/simd.h

# ============================================================================
# Build targets
# ============================================================================

all: task1 task2 task3 task4

task1: src/task1.c $(FRAMEWORK_SRC) $(FRAMEWORK_HDR)
	$(CC) $(CFLAGS) -DTASK_ID=1 src/task1.c $(FRAMEWORK_SRC) -o $@ $(LDFLAGS)

task2: src/task2.c $(FRAMEWORK_SRC) $(FRAMEWORK_HDR)
	$(CC) $(CFLAGS) -DTASK_ID=2 src/task2.c $(FRAMEWORK_SRC) -o $@ $(LDFLAGS)

task3: src/task3.c src/simd.c $(FRAMEWORK_SRC) $(FRAMEWORK_HDR)
	$(CC) $(CFLAGS) -DTASK_ID=3 src/task3.c src/simd.c $(FRAMEWORK_SRC) -o $@ $(LDFLAGS)

task4: src/task4.c src/simd.c $(FRAMEWORK_SRC) $(FRAMEWORK_HDR)
	$(CC) $(CFLAGS) -DTASK_ID=4 src/task4.c src/simd.c $(FRAMEWORK_SRC) -o $@ $(LDFLAGS)

# ============================================================================
# Data generation  (MUST be run before check / grade)
# ============================================================================

gen_data:
	$(PYTHON) data/gen_data.py
	$(PYTHON) data/reference_sdpa.py

# ============================================================================
# Correctness checks
# ============================================================================

check_task1: task1
	@echo "--- Task 1: Correctness ---"
	./task1 --data data/tiny/meta.txt --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/tiny/meta.txt data/tiny/out.bin
	./task1 --data data/small/meta.txt --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/small/meta.txt data/small/out.bin
	@echo "Task 1: ALL PASSED"
	@echo

check_task2: task2
	@echo "--- Task 2: Correctness ---"
	./task2 --data data/tiny/meta.txt --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/tiny/meta.txt data/tiny/out.bin
	./task2 --data data/small/meta.txt --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/small/meta.txt data/small/out.bin
	@echo "Task 2: ALL PASSED"
	@echo

check_task3: task3
	@echo "--- Task 3: Correctness ---"
	./task3 --data data/tiny/meta.txt --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/tiny/meta.txt data/tiny/out.bin
	./task3 --data data/small/meta.txt --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/small/meta.txt data/small/out.bin
	@echo "Task 3: ALL PASSED"
	@echo

check_task4: task4
	@echo "--- Task 4: Correctness ---"
	./task4 --data data/tiny/meta.txt --threads 4 --pin-cores --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/tiny/meta.txt data/tiny/out.bin
	./task4 --data data/small/meta.txt --threads 4 --pin-cores --repeat 1 --warmup 0 --quiet
	$(PYTHON) test/check_correctness.py data/small/meta.txt data/small/out.bin
	@echo "Task 4: ALL PASSED"
	@echo

check: check_task1 check_task2 check_task3 check_task4
	@echo "All correctness checks passed."

# ============================================================================
# Performance grading
# ============================================================================

grade: all
	$(PYTHON) test/bench.py

# ============================================================================
# Upper-bound comparison  (installs PyTorch if needed)
# ============================================================================

upper_bound: all
	@$(PYTHON) -c "import torch" 2>/dev/null || \
		(echo "PyTorch not found, installing from Tsinghua mirror..." && \
		 $(PIP) install torch -i $(PYPI_MIRROR))
	$(PYTHON) test/upper_bound.py

# ============================================================================
# Clean
# ============================================================================

clean:
	rm -f task1 task2 task3 task4
	rm -f data/*/out.bin
