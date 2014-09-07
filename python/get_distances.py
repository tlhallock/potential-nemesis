#!/usr/bin/python

import requests
import os
import shutil
import random
import sys

def encode_locs(locs):
    url = locs[0]
    for i in range(1, len(locs)):
        url = url + "|" + locs[i]
    return url

def download_distances(locs):
    encoded = encode_locs(locs)
    url = "http://maps.googleapis.com/maps/api/distancematrix/json?origins=" + encoded + "&destinations=" + encoded + "&mode=driving&language=en-US&units=imperial"
    file = requests.get(url, stream=True)
    return file.raw

def save_locations(locs, filename):
    with open(filename + ".locs", "wb") as location:
        location.write(encode_locs(locs))

def save_distances(locs, filename):
    dump = download_distances(locs)
    save_locations(locs, filename)
    with open(filename, 'wb') as location:
        shutil.copyfileobj(dump, location)
    del dump

# Denver lower bound:  39.558185, -105.226243
# Denver upper bound:  40.211516, -104.745591
def get_random_point():
    return str(random.uniform(39.558185, 40.211516)) + "," + str(random.uniform(-105.226243, -104.745591))

def get_locs(num):
    ls = []
    for i in range(num):
        ls.append(get_random_point())
    return ls

def save_several_distances(num, num_in_each):
    for i in range(num):
        save_distances(get_locs(num_in_each), "./distances." + str(i) + ".json");
        print("Saved set ", i);

if len(sys.argv) < 3:
    print("Usage: " + sys.argv[0] + " <number of queries to make> <number of locations in each>")
else:
    save_several_distances(int(sys.argv[1]), int(sys.argv[2]));


