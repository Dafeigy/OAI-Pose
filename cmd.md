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
sudo ./build_oai -w USRP --ninja --gNB -c
```
# Run OAI gNB

### USRP B210
```bash
cd ~/openairinterface5g
source oaienv
cd cmake_targets/ran_build/build
# gNB & core network run in different machine
sudo ./nr-softmodem -O ../../../srs.conf --sa -E --continuous-tx
# gNB & core network run in teh same local machines
sudo ./nr-softmodem -O ../../../srs-lo.conf --sa -E --continuous-tx
```