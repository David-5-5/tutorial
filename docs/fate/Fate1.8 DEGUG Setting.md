# Fate1.8 DEGUG Setting

[TOC]

## A. 配置fateflow/bin/service.sh文件

```shell
# line 106
exec python ${FATE_FLOW_BASE}/python/fate_flow/fate_flow_server.py >> "${log_dir}/console.log" 2>>"${log_dir}/error.log"
# modify to
exec python -m debugpy --listen 0.0.0.0:5678 ${FATE_FLOW_BASE}/python/fate_flow/fate_flow_server.py >> "${log_dir}/console.log" 2>>"${log_dir}/error.log"

# line 110
nohup python ${FATE_FLOW_BASE}/python/fate_flow/fate_flow_server.py >> "${log_dir}/console.log" 2>>"${log_dir}/error.log" &

nohup python -m debugpy --listen 0.0.0.0:5678 ${FATE_FLOW_BASE}/python/fate_flow/fate_flow_server.py >> "${log_dir}/console.log" 2>>"${log_dir}/error.log" &
```

## B 配置.env文件

```shell
PYTHONPATH=./python:./python/fate_client:./fateflow/python/:./eggroll/python/
FATE_PROJECT_BASE=./
EGGROLL_HOME=./eggroll


# Begin execute examples in console, set PYTHONPATH under FATE DIRECTORY
# export PYTHONPATH=$PWD/python:$PWD/python/fate_client:$PWD/fateflow/python/:$PWD/eggroll/python/
```

## C 配置.vscode/launch.json文件

For remote debugging, The envFile is very IMPORTANT!!!. And the detail configuration as
following:

```JSON
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: Attach",
            "type": "python",
            "request": "attach",
            "connect": {
                "host": "127.0.0.1",
                "port": 5678
            }
        }
    ]
}
```

## D 配置.vscode/launch.json文件

For unit-testing, the detail configuration as following:

```JSON
{
    "java.compile.nullAnalysis.mode": "disabled",
    "python.testing.unittestArgs": [
        "-v",
        "-s",
        ".",
        "-p",
        "*_test.py"
    ],
    "python.testing.pytestEnabled": false,
    "python.testing.unittestEnabled": true,
    "python.envFile": "${workspaceFolder}/.env",
    "java.jdt.ls.vmargs": "-XX:+UseParallelGC -XX:GCTimeRatio=4 -XX:AdaptiveSizePolicyWeight=90 -Dsun.zip.disableMemoryMapping=true -Xmx4G -Xms100m -Xlog:disable"
}
```

## D 配置.fate\_profile文件

```SHELL
# The enviroment for execute examples
export PYTHONPATH=${PWD}/python:${PWD}/python/fate_client:${PWD}/fateflow/python/:${PWD}/eggroll/python/

bin/init_env.sh
Set PYTHONPATH with installaltion directory
export PYTHONPATH=/home/luming/workspace/FATE/python:/home/luming/workspace/FATE/fateflow/python
python/fate_client/pipeline/config.yaml
ip: 127.0.0.1
port: 9380
```

ComputingType - ComputingEngine

## 参考

### examples/config.yaml

```YAML
# Set with installaltion directory
data_base_dir: "/home/luming/workspace/FATE" # pa th to project base where data is located
```

### examples/pipeline/demo/pipeline-upload.py

```python
# Set with installaltion directory
DATA_BASE = "/home/luming/workspace/FATE"
```

