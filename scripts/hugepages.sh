#!/bin/bash

set -xe

sudo sh -c 'for i in /sys/devices/system/node/node*/hugepages/hugepages-2048kB/nr_hugepages; do echo 512 > $i; done'
sudo mkdir -p /mnt/huge
sudo mount -t hugetlbfs nodev /mnt/huge
