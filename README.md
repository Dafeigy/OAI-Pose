## Extra dependencies
```bash
cd NR-Pose
# TODO: write in build_oai -I
git clone https://github.com/protobuf-c/protobuf-c.git
git clone https://github.com/protocolbuffers/protobuf.git
```

## Build OAI-Pose

```bash
cd NR-pose
source oaienv
cd cmake_targets
sudo ./build_oai -w USRP --ninja --gNB -c
```

# Run OAI-pose
```bash
cd NR-Pose
source oaienv
cd cmake_targets/ran_build/build
# gNB & core network run in different machine
sudo ./nr-softmodem -O ../../../srs.conf --sa -E --continuous-tx
# gNB & core network run in teh same local machines
sudo ./nr-softmodem -O ../../../srs-lo.conf --sa -E --continuous-tx
# gNB & core network run in different machine in Sony environment
sudo ./nr-softmodem -O ../../../srs-sony.conf --sa -E --continuous-tx

sudo ./nr-softmodem -O ../../../srs-sony-oxg.conf --sa -E

####### N310
sudo ./ran_build/build/nr-softmodem -O ../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb.band78.sa.fr1.106PRB.2x2.usrpn310.conf --gNBs.[0].min_rxtxtime 6 --sa --usrp-tx-thread-config 1


## Run OAI nrUE

```bash
sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --ue-fo-compensation --sa -E --uicc0.imsi 466920000000003
```