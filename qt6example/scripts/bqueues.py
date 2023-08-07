#! /usr/bin/env python3

import argparse
import sys
import random
def randomize(_max):
  runint = random.randint(0,_max)
  if(runint == _max): 
    pendint = random.randint(0,8)
  else:
    pendint = 0
 
  return pendint,runint
 
parser = argparse.ArgumentParser()
parser.add_argument('--out',type=str,required=True)

lines = [
'QUEUE_NAME  HOST     PRIO STATUS       MAX JL/U JL/P JL/H NJOBS PEND RUN SUSP',
'Regression  reynaldo 10   Open::Active   -    -    -    -   nj  pnd  rn  sus',
'LongJobs    reynaldo 10   Open::Active   -    -    -    -   nj  pnd  rn  sus',
'ShortJobs   reynaldo 10   Open::Active   -    -    -    -   nj  pnd  rn  sus',
'Interactive bernardo 10   Open::Active   -    -    -    -   nj  pnd  rn  sus',
]

debug = False

args = parser.parse_args()

with open(args.out,'w') as f:
  f.write(lines[0]+'\n')
  if(debug): print(lines[0])

  # Regression
  line = lines[1].replace('nj','32')

  pendint,runint = randomize(32)

  line = line.replace('pnd',str(pendint))
  line = line.replace('rn',str(runint))
  line = line.replace('sus','0')
  f.write(line+'\n')
  if(debug): print(line)

  # LongJobs
  line = lines[2].replace('nj','16')
  pendint,runint = randomize(16)
  line = line.replace('pnd',str(pendint))
  line = line.replace('rn',str(runint))
  line = line.replace('sus','0')
  f.write(line+'\n')
  if(debug): print(line)

  # ShortJobs
  line = lines[3].replace('nj','8')
  pendint,runint = randomize(8)
  line = line.replace('pnd',str(pendint))
  line = line.replace('rn',str(runint))
  line = line.replace('sus','0')
  f.write(line+'\n')
  if(debug): print(line)


  # Interactive
  line = lines[4].replace('nj','4')

  pendint,runint = randomize(4)
  line = line.replace('pnd',str(pendint))
  line = line.replace('rn',str(runint))
  line = line.replace('sus','0')
  f.write(line+'\n')
  if(debug): print(line)

f.close()
