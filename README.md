# Qt System Monitor Application

TODO --ADD HERE PHOTO OF THE MAIN WINDOW :smile:

# What is this? :book:

This is a `QtQuick` (Qt5/QML) application which represents a small system monitor for the `Linux Ubuntu` operating system.
User can find the following system data information when this application is started, and all of them are shown on screen and updated automatically in real-time:

- CPU load  
- Number of threads and processes
- Memory info (available, used, total, cache)
- Disk info (currently only information about solid disks is presented on the GUI side, which are registered on the system as `/dev/sd*` disks)

# Requirements & Build :wrench: 
To be able to start this application on your computer, you should have installed `Linux Ubuntu` operating system. Required packages (Qt libraries) can be installed by running `install_packages.sh` bash script. To be able to execute this script, you should give it executable permissions. This can be done with command:
```
chmod +x install_packages.sh 
```
After that, script can be run in terminal with command: 
```
./install_packages.sh
```

After all packages from the script are installed, application can be built by executing `start.sh` script. This script also should have executable permissions.

# How is it implemented? :brain:
The system data about disks, memory, CPUs, processes and threads is gathered by running commands in terminal, from the application. Each command is executed as independent process (QProcess) inside its own class, in C++. To be able to update everything without blocking other threads, each class extends `QThread` and implements method `run()`. Below, exact used commands will be explained in more detail.

## CPU load :computer:
CPU load is retrieved by calling command: 
```
cat /proc/stat | grep 'cpu'
```
This returns available information about each CPU operating on the computer. The way CPU load is presented in the application and what can be found inside `/proc/stat/`, is explained in detail at:  
  - <https://rosettacode.org/wiki/Linux_CPU_utilization#UNIX_Shell>,
  - <https://supportcenter.checkpoint.com/supportcenter/portal?eventSubmit_doGoviewsolutiondetails=&solutionid=sk65143>,
  - <https://www.kgoettler.com/post/proc-stat/>.

## Disk info :cd:
Disk info is gathered by calling three very similar commands. They return how much available, used and total space is there on the disk.  

First one gathers information about solid disks only:
```
df -h --output=source,size,avail,used | egrep '/dev/sd'
```
Information about floppy disks and other disks was fetched by calling these two commands:
```
df -h --output=source,size,avail,used | egrep '/dev/fd'

df -h --output=source,size,avail,used | egrep -v '/dev/(sd.|fd.)'
```

For more detailed explanation about fetching disk information, visit this page: 
- https://help.ubuntu.com/lts/installation-guide/armhf/apcs04

## Memory info :file_folder:
Memory info is retrieved with this command:
```
free -m | head -n 2 | tail -n 1
```
Along with some other data, this returns available, used, total and cache memory usage. 

## Threads & Processes :bulb:
Number of threads is retrieved with:
```
ps -eo nlwp --no-headers | awk '{ num_threads += $1 } END { print num_threads }'
```

and number of processes with:
```
ps -e --no-headers | wc -l
```

Above mentioned `ps` command reports a snapshot of the current processes.

*You can learn more about all used commands through `man` pages (example command: `man ps`).*

## Connection between QML and C++
Every class is created inside `main.cpp` and each thread is started from there.
`Q_PROPERTY` is used for connecting data from `C++` to `QML`. For example, data about CPU load is connected to GUI side with this line in code:
```
Q_PROPERTY(QVariantMap cpuMap READ cpuMap WRITE setCpuMap NOTIFY cpusChanged)
```

# Improvements :art:
- GUI side is currently basic and its style can be improved. For example: progress bar can be nicer, charts can be added...
- Thread termination in `main.cpp` should be implemented in a safer manner.
