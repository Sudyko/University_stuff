#!/bin/bash

fio_test_base() {
sudo fio --filename=test testfile --direct=1 --ioengine=libaio --time_based --group_reporting --runtime=5 --eta-newline=1 --size=64MiB --output-format=terse $@
}
fio_test_latency() {
fio_test_base --bs=4k --iodepth=1 --numjobs=1 $@
}
fio_test_throughput() {
fio_test_base --bs=64k --iodepth=64 --numjobs=4 $@
}
fio_test_iops() {
fio_test_base --bs=4k --iodepth=256 --numjobs=4 $@
}

for name in "jfs" "btrfs" "reiserfs" "f2fs"
do
dd if=/dev/zero of=fs.bin bs=1M count=256
if [[ $name == "ext4" ]]; then
	sudo mkfs -t $name -F fs.bin
else
sudo mkfs -t $name -f fs.bin
fi
sudo mount fs.bin ./fs_folder
cd ./fs_folder
sudo touch test testfile
echo "terse_version_3;fio_version;jobname;groupid;error;read_kb;read_bandwidth_kb;read_iops;read_runtime_ms;read_slat_min_us;read_slat_max_us;read_slat_mean_us;read_slat_dev_us;read_clat_min_us;read_clat_max_us;read_clat_mean_us;read_clat_dev_us;read_clat_pct01;read_clat_pct02;read_clat_pct03;read_clat_pct04;read_clat_pct05;read_clat_pct06;read_clat_pct07;read_clat_pct08;read_clat_pct09;read_clat_pct10;read_clat_pct11;read_clat_pct12;read_clat_pct13;read_clat_pct14;read_clat_pct15;read_clat_pct16;read_clat_pct17;read_clat_pct18;read_clat_pct19;read_clat_pct20;read_tlat_min_us;read_lat_max_us;read_lat_mean_us;read_lat_dev_us;read_bw_min_kb;read_bw_max_kb;read_bw_agg_pct;read_bw_mean_kb;read_bw_dev_kb;write_kb;write_bandwidth_kb;write_iops;write_runtime_ms;write_slat_min_us;write_slat_max_us;write_slat_mean_us;write_slat_dev_us;write_clat_min_us;write_clat_max_us;write_clat_mean_us;write_clat_dev_us;write_clat_pct01;write_clat_pct02;write_clat_pct03;write_clat_pct04;write_clat_pct05;write_clat_pct06;write_clat_pct07;write_clat_pct08;write_clat_pct09;write_clat_pct10;write_clat_pct11;write_clat_pct12;write_clat_pct13;write_clat_pct14;write_clat_pct15;write_clat_pct16;write_clat_pct17;write_clat_pct18;write_clat_pct19;write_clat_pct20;write_tlat_min_us;write_lat_max_us;write_lat_mean_us;write_lat_dev_us;write_bw_min_kb;write_bw_max_kb;write_bw_agg_pct;write_bw_mean_kb;write_bw_dev_kb;cpu_user;cpu_sys;cpu_csw;cpu_mjf;cpu_minf;iodepth_1;iodepth_2;iodepth_4;iodepth_8;iodepth_16;iodepth_32;iodepth_64;lat_2us;lat_4us;lat_10us;lat_20us;lat_50us;lat_100us;lat_250us;lat_500us;lat_750us;lat_1000us;lat_2ms;lat_4ms;lat_10ms;lat_20ms;lat_50ms;lat_100ms;lat_250ms;lat_500ms;lat_750ms;lat_1000ms;lat_2000ms;lat_over_2000ms;disk_name;disk_read_iops;disk_write_iops;disk_read_merges;disk_write_merges;disk_read_ticks;write_ticks;disk_queue_time;disk_util" > ../$name.csv
echo "Testing $name filesystem for latency..."
for (( a = 0; a < 5; a++ ))
do
fio_test_latency --rw=randread --name=$name-readlatency >> ../$name.csv
fio_test_latency --rw=randwrite --name=$name-writelatency >> ../$name.csv
fio_test_latency --rw=randrw --name=$name-readwritelatency >> ../$name.csv
done
echo "Testing $name filesystem for random I/O throughput..."
for (( a = 0; a < 5; a++ ))
do
fio_test_throughput --rw=randread --name=$name-randomread >> ../$name.csv
fio_test_throughput --rw=randwrite --name=$name-randomwrite >> ../$name.csv
fio_test_throughput --rw=randrw --name=$name-randomreadwrite >> ../$name.csv
done
echo "Testing $name filesystem for random I/O IOPS..."
for (( a = 0; a < 5; a++ ))
do
fio_test_iops --rw=randread --name=$name-randomread >> ../$name.csv
fio_test_iops --rw=randwrite --name=$name-randomwrite >> ../$name.csv
fio_test_iops --rw=randrw --name=$name-randomreadwrite >> ../$name.csv
done
echo "Testing $name filesystem for sequential I/O throughput..."
for (( a = 0; a < 5; a++ ))
do
fio_test_throughput --rw=read --name=$name-seqread >> ../$name.csv
fio_test_throughput --rw=write --name=$name-seqwrite >> ../$name.csv
fio_test_throughput --rw=rw --name=$name-seqreadwrite >> ../$name.csv
done
echo "Testing $name filesystem for sequential I/O IOPS..."
for (( a = 0; a < 5; a++ ))
do
fio_test_iops --rw=read --name=$name-seqread >> ../$name.csv
fio_test_iops --rw=write --name=$name-seqwrite >> ../$name.csv
fio_test_iops --rw=rw --name=$name-seqreadwrite >> ../$name.csv
done
cd ..
sudo umount fs.bin
sudo rm -rf fs.bin
done