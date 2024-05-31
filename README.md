## Enable Proto transmit

Before compile, cancel the annotation `#def DO_PROTO` in `openair1/PHY/NR_ESTIMATION/nr_ul_channel_estimation.c` to enable proto message repost.



## Extra dependencies
```bash
cd NR-Pose
# TODO: write in build_oai -I
git clone https://github.com/protobuf-c/protobuf-c.git
git clone https://github.com/protocolbuffers/protobuf.git
```

## Before run

```bash
sudo route add -net 10.60.0.0 netmask 255.255.255.0 gw 192.168.0.133

sudo route add -net 10.61.0.0 netmask 255.255.255.0 gw 192.168.0.133


```

## Build OAI-Pose

```bash
cd NR-pose
source oaienv
cd cmake_targets
```

## Run OAI-pose
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

## Run OAI nrUE with N310
```bash
sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --ue-fo-compensation --sa --uicc0.imsi 466920000000003 --usrp-args "addr=192.168.20.2"
```

## Run gNB 4x4 MIMO
```bash
sudo ./ran_build/build/nr-softmodem -O ../targets/PROJECTS/GENERIC-NR-5GC/CONF/162PRB.4x4.conf --gNBs.[0].min_rxtxtime 6 --sa --usrp-tx-thread-config 1
```

## B210 
```bash
sudo ./ran_build/build/nr-softmodem -O ../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb.sa.band78.fr1.106PRB.usrpb210.conf --gNBs.[0].min_rxtxtime 6 --sa --usrp-tx-thread-config 1 -E
```
## N310 13900K

```bash
sudo ./ran_build/build/nr-softmodem -O ../band78-106.conf --gNBs.[0].min_rxtxtime 6 --sa --usrp-tx-thread-config 1
```

## DATA COLLECTION

|------- R -------|------- L-------|------- L -------|------- R -------|
|---Start Stand---|---Start Fall---|---Lying on bed--|-----End Fall----|

## Data Process Scripts:
See NR-FALL-data processing