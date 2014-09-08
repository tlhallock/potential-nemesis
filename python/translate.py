#!/usr/bin/python

import os
import json

def get_coords(f):
	with open(f + ".locs", "r") as locsfile:
		return locsfile.read().split("|")

def write_object(f, js):
	coo = get_coords(f);
	l = len(js['destination_addresses'])
	delim = "\t"
	fout = f + ".dst.out"
	print(fout)
	out = open(fout, "w")
	out.write(str(l) + "\n")
	for i in range(l):
		rco = coo[i].split(',')
		s = js['destination_addresses'][i].encode("utf-8")
		out.write(str(i) + delim + rco[0] + delim + rco[1] + delim + "'" + s + "'" + "\n")
	for i in range(l):
		for j in range(l):
			di = js['rows'][i]['elements'][j]['distance']['value']
			du = js['rows'][i]['elements'][j]['duration']['value']
			out.write(str(i) + delim + str(j) + delim + str(du) + delim + str(di) + "\n");


def get_json(f):
	#print("Opening ", f)
	with open(f, "r") as jsonfile:
		return json.loads(jsonfile.read())


for f in os.listdir("."):
	if not os.path.isfile(f):
		continue
	if not f.endswith(".json"):
		continue
	write_object(f, get_json(f))
	