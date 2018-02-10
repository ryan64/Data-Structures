#!/bin/bash
# Copyright (C) 2013-2016 Yiqun Zhang <zhangyiqun9164@gmail.com>
# All Rights Reserved.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# this is the root path of the course directory.
filename="densemult"
casecount=3
timeout="10s"

echo -e "\033[1;93mProgram name is $filename.\033[0m"
for casenum in `seq 1 1 $casecount`; do
    echo -e "\033[1;93mTest case $casenum\033[0m"
    timeout -k $timeout $timeout ./$filename "A=$casenum.txt;C=$casenum.out" 1>$casenum.stdout 2>$casenum.stderr 
    if [ $? -ne 0 ]; then
        echo -e "\t\033[1;91mProgram killed due to timeout ($timeout).\033[0m"
        echo "Test case $casenum timed out ($timeout)." >> TIMEOUT
    fi
    diff -iEBwu $casenum.ans $casenum.out > $casenum.diff
    if [ $? -ne 0 ]; then
        echo -e "    \033[1;91mFAILED.\033[0m"
    else
        echo -e "    \033[1;92mPASSED.\033[0m"
        rm -f $casenum.diff
    fi
done

