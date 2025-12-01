#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"

#define CHECK_FATAL(cond, fmt, ...) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "\n❌ Critical test failed at %s:%d\n", __FILE__, __LINE__); \
            fprintf(stderr, "   → " fmt "\n", ##__VA_ARGS__); \
            exit(1); \
        } \
    } while (0)

#define CHECK_WARN(cond, fmt, ...) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "\n⚠️  Non-critical test failed at %s:%d\n", __FILE__, __LINE__); \
            fprintf(stderr, "   → " fmt "\n", ##__VA_ARGS__); \
            warn_count++; \
            break; \
        } \
    } while (0)

#define INFO(fmt, ...) printf("▶ " fmt "\n", ##__VA_ARGS__)

int main(void) {
    printf("===== HASH TABLE AUTOMATED TESTS =====\n\n");

    int warn_count = 0;
    int val = 0;

    // --- Test 1: Initialization ---
    INFO("Test 1: Initialization of hash table");
    hash_table_t *ht = ht_init(8);
    CHECK_FATAL(ht != NULL, "ht_init() returned NULL");

    // --- Test 2: Basic insert and search ---
    INFO("Test 2: Insert and search basic keys");
    CHECK_FATAL(ht_insert(ht, 10, 100), "ht_insert(10, 100) failed");
    CHECK_FATAL(ht_insert(ht, 20, 200), "ht_insert(20, 200) failed");
    CHECK_FATAL(ht_search(ht, 10, &val) && val == 100,
                "ht_search(10) expected 100, got %d", val);
    CHECK_FATAL(ht_search(ht, 20, &val) && val == 200,
                "ht_search(20) expected 200, got %d", val);

    // --- Test 3: Overwrite existing key ---
    INFO("Test 3: Overwriting existing key");
    CHECK_FATAL(ht_insert(ht, 10, 999), "failed to overwrite key=10");
    CHECK_FATAL(ht_search(ht, 10, &val) && val == 999,
                "overwrite check failed: expected 999, got %d", val);

    // --- Test 4: Search nonexistent key ---
    INFO("Test 4: Searching for nonexistent key");
    CHECK_FATAL(!ht_search(ht, 9999, &val),
                "ht_search(9999) should fail but returned success");

    // --- Test 5: Large number of inserts ---
    INFO("Test 5: Many inserts and collision handling");
    do {
        bool ok = true;
        for (int i = 0; i < 2000; i++) {
            if (!ht_insert(ht, i, i * 2)) { ok = false; break; }
        }
        for (int i = 0; i < 2000 && ok; i++) {
            if (!ht_search(ht, i, &val) || val != i * 2) { ok = false; break; }
        }
        CHECK_WARN(ok, "Large-scale insert/search failed (possible collision or resize issue)");
    } while (0);

    // --- Test 6: Robustness / invalid input handling ---
    INFO("Test 6: Robustness (handling invalid pointers)");
    do {
        bool ok = true;
        if (ht_insert(NULL, 1, 1)) ok = false;
        if (ht_search(NULL, 1, &val)) ok = false;
        ht_free(NULL); // should not crash
        CHECK_FATAL(ok, "Invalid pointer handling failed");
    } while (0);

    // --- Test 7: Freeing memory ---
    INFO("Test 7: Freeing memory (should not crash)");
    ht_free(ht);

    printf("\n========================================\n");
    if (warn_count > 0) {
        printf("⚠️  Passed with %d non-critical warning(s)\n", warn_count);
        printf("   → You may fix these to earn extra credit.\n");
    } else {
        printf("✅ All tests passed successfully!\n");
    }
    printf("========================================\n");
    return 0;
}