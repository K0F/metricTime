# Metric time for everyone

Utility thet converts babylonian to metric time. Day has 20h and it is divided linearly. One 1dh = 1.2h. Day hour has 100 minutes, minute has 100 seconds. One 1ds = 0.432s or 2,3147Hz.


## Usage

  ```./dh [unix time]```

  That will output something as following:


  ```bash
  Standard:     13:30:14
  -------------------------
  Metric UI:    11.25.33
  Metric Float: 11,2533 dh
```


## Build

```bash
make
```
