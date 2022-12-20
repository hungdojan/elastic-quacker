#include "key_seqv.h"

static size_t key_seqv_index = 0;

// key sequences for Windows systems
static const struct key_seqv_t key_seqvs[] = {
};

bool get_next_kbc(struct key_seqv_t *const report_out) {
    if (report_out == NULL)
        return false;
    if (key_seqv_index >= sizeof(key_seqvs))
        return false;

    *report_out = key_seqvs[key_seqv_index++];
    return true;
}

/* key_seqv.c */
