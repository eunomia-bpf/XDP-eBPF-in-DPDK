# XDP in userspace eBPF with DPDK

## XDP examples

## Compile and run

To get and build dpdk from the root project directory:

```sh
git submodule update --init --recursive
make dpdk
```

To build the project:

```sh
export PKG_CONFIG_PATH=<the path of the pkgconfig directory inside dpdk>
make build
```

To run a very simple test:

In one terminal window

```sh
sudo ./build/base-server -l 0 --vdev=net_tap0,iface=tapdpdk
```

In another terminal window:

```sh
sudo ./scripts/testbed-setup.sh
sudo arping -i veth0 1.2.3.4
```
