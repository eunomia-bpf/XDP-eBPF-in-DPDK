To get and build dpdk from the root project directory:

```
git submodule update --init --recursive
make dpdk
```

To build the project:
```
export PKG_CONFIG_PATH=<the path of the pkgconfig directory inside dpdk>
make build
```

To run a very simple test:

In one terminal window
```
sudo ./build/base-server -l 0 --vdev=net_tap0,iface=tapdpdk
```

In another terminal window:
```
sudo ./scripts/testbed-setup.sh
sudo arping -i veth0 1.2.3.4
```
