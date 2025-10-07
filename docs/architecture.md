                     ┌──────────────────────────────┐
                     │         controlplane         │
                     │  Node.js (API + Policy)      │
                     │  - REST/gRPC endpoints       │
                     │  - Tenant & Policy storage   │
                     │  - Auth (OIDC/JWT)           │
                     └──────────────┬───────────────┘
                                    │
                                    │ (control channel: HTTPS/gRPC)
                                    ▼
        ┌────────────────────────────────────────────┐
        │                dataplane                   │
        │  Go Agent (cs-firewalld)                   │
        │    - Loads eBPF/XDP programs               │
        │    - Manages firewall rules per tenant     │
        │    - Exposes Prometheus metrics            │
        │    - Hot reloads policies from controller  │
        │                                            │
        │  eBPF (XDP) program in kernel              │
        │    - Enforces L3/L4 allow/deny             │
        │    - Maintains per-tenant counters/maps    │
        └────────────────────────────────────────────┘
                                    │
                             (packet path)
                                    ▼
                              Linux Kernel
                             (Ethernet NIC)
