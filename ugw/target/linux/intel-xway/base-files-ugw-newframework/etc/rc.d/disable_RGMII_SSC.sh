#!/bin/sh
#This script is used to disable RGMII SSC to default values for testing purposes.
#Default values are applied after executing this script.

disable_RGMII_SSC() {
		echo "Disabling RGMII SSC ..."
		sleep 1
		mem -s 0x16200044 -w 0x0000 -u > /dev/null;
		mem -s 0x16200048 -w 0x0000 -u > /dev/null;
		mem -s 0x1620004c -w 0x0000 -u > /dev/null;
		mem -s 0x16200050 -w 0x0000 -u > /dev/null;
		mem -s 0x16200054 -w 0x0000 -u > /dev/null;
		mem -s 0x16200058 -w 0x0000 -u > /dev/null;
		mem -s 0x1620005C -w 0x0000 -u > /dev/null;
		mem -s 0x16200060 -w 0x0000 -u > /dev/null;
		mem -s 0x1620003C -w 0x0000 -u > /dev/null;
		mem -s 0x1620003C -w 0x0000 -u > /dev/null;
		mem -s 0x1620003C -w 0x0000 -u > /dev/null;

}

disable_RGMII_SSC;
