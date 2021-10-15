# PyC
## Setup
In the root of the repository:
```shell
sudo ./setup.h
```
## Creating a module
Anywhere:
```shell
create_pyc_module <module_name>
$EDITOR <module_name>/<module_name>_src.cpp
```
Then, import your c++ functions or classes and wrap them according to [boost::python API](https://www.boost.org/doc/libs/1_76_0/libs/python/doc/html/tutorial/index.html) 

Then, compile it, using:
```shell
compile_pyc_module <module_name>
```
This command will create the `<module_name>.so` file, which acts like real python module
## Usage
In the same folder with `<module_name>.so`:
```python
import <module_name>
```
or
```python
from <module_name> import <something_from_the_module> 
```
or anyway you want.

## Uninstallation
```shell
sudo ./uninstall.sh
```