# Cipherplane

**Cipherplane** is a learning and research monorepo exploring the design of a modern Zero-Trust network stack.

## 🧩 Structure

| Folder          | Description                                                          |
| --------------- | -------------------------------------------------------------------- |
| `dataplane/`    | Go data-plane agent using eBPF/XDP for high-speed packet filtering.  |
| `controlplane/` | Node.js orchestration plane managing tenants, policies, and metrics. |
| `docs/`         | Design notes, diagrams, and architecture decisions.                  |

## 🚀 Goals

- [x] Attach minimal XDP program and verify it runs on Raspberry Pi.
- [ ] Add counter map and Prometheus metrics in Go agent.
- [ ] Build control-plane API (Node.js) to push policies.
- [ ] Implement live map updates and secure agent registration.

## 🛠️ Development

**On Raspberry Pi**

```bash
make bpf
sudo ip link set dev enxb827... xdpgeneric obj dataplane/ebpf/xdp_count.bpf.o sec xdp
sudo bpftool net
```
