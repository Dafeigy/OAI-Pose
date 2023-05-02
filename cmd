# Install OAI dependencies
```bash
cd ~/openairinterface5g/cmake_targets
./build_oai -I
```
# Build OAI gNB
```bash
cd ~/openairinterface5g
source oaienv
cd cmake_targets
./build_oai -w USRP --ninja --gNB -c
```
# Run OAI gNB

### USRP B210
```bash
cd ~/openairinterface5g
source oaienv
cd cmake_targets/ran_build/build
sudo ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb.sa.band78.fr1.106PRB.usrpb210.conf --sa -E --continuous-tx
```