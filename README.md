# Hardware Search Rest API
C++ search engine for hardware with REST API

# Features

Users can:
 - Get info for certain query
 - Buy hardware
 - Check difference between multiple hardware
 - Upload new data
 
# Sample of json request for info

Rest is simple ``query``

```json
{
    "action": "diff",
    "queries": [
        {
            "type": "cpu",
            "manufacturer": "=;INTEL",
            "generation": "=;12",
            "cores" :"=;16"
        },
        {
            "type": "cpu",
            "manufacturer": "=;AMD",
            "generation": "=;5000",
            "cores" :"=;16"
        }
    ]
}
```

# Sample of request for uploading data

Sent POST with ``/add?name=market1``, which means it is market1 that is getting new data

```txt
CPU|10|2
CPU|20|3
Motherboard|8|3
Motherboard|16|2
Motherboard|21|1
GPU|5|3
GPU|7|2
GPU|10|2
RAM|8|8
RAM|10|8
RAM|12|8
PowerSupply|7|4
PowerSupply|9|6
PowerSupply|11|4
PcCase|4|6
PcCase|6|4
Cooler|5|3
Cooler|7|3
SSD|5|4
SSD|9|4
```
