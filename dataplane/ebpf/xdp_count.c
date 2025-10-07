#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

#define SEC(NAME) __attribute__((section(NAME), used))
typedef __u32 u32;
typedef __u64 u64;

/*
 * Define a simple map:
 * - type: PERCPU_ARRAY
 * - key: u32 (only key 0)
 * - value: u64 (packet count)
 */
struct bpf_map_def {
    u32 type;
    u32 key_size;
    u32 value_size;
    u32 max_entries;
    u32 map_flags;
};

SEC("maps")
struct bpf_map_def pkt_cnt = {
    .type = BPF_MAP_TYPE_PERCPU_ARRAY,
    .key_size = sizeof(u32),
    .value_size = sizeof(u64),
    .max_entries = 1,
};

/* Minimal helper declaration — normally from bpf_helpers.h */
static void *(*bpf_map_lookup_elem)(void *map, const void *key) = (void *)BPF_FUNC_map_lookup_elem;

/*
 * XDP function:
 * - Look up key 0 in pkt_cnt map.
 * - If found, increment per-CPU counter.
 * - Return XDP_PASS to let the packet continue.
 */
SEC("xdp")
int xdp_count(struct xdp_md *ctx)
{
    u32 key = 0;
    u64 *val = bpf_map_lookup_elem(&pkt_cnt, &key);
    if (val)
        (*val)++;

    return XDP_PASS;
}

SEC("license")
const char __license[] = "GPL";