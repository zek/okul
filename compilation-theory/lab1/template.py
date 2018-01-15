#!/usr/bin/python

from __future__ import print_function
import os
import sys
import re
import codecs
import pprint
from datetime import date

pp = pprint.PrettyPrinter(indent=4)


def processFile(filepath):
    fp = codecs.open(filepath, 'rU', 'iso-8859-2')

    content = fp.read()

    # author
    meta_tags = {x[0]: x[1] for x in re.findall(r'<META.*NAME="(.*)".*CONTENT="(.*)".*>', content)}
    keywords = ", ".join([meta_tags['KLUCZOWE_1'], meta_tags['KLUCZOWE_2'], meta_tags['KLUCZOWE_3']])

    # matches all p tags
    pat = re.compile(r"<p>(.*?)<\/p>", re.MULTILINE | re.DOTALL | re.IGNORECASE)
    pat2 = re.compile(r"<.*?>", re.MULTILINE | re.DOTALL | re.IGNORECASE)

    # abbreviations
    abbreviations = re.compile(r"\b[a-zA-Z]{3}\.", re.MULTILINE | re.DOTALL)
    abbreviation_list = []

    # match numbers between 0-65535
    numbers = re.compile(r"\b([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])\b")
    number_list = []

    #floats
    floats = re.compile(r"\b[+-]?(?:(?:\d+\.(?: )?\d*)|(?:\.\d+))(?:e[+-]\d*)?\b")
    float_list = []

    #emails
    emails = re.compile(r"\b[\w\.]+@(?:[a-zA-Z_]+\.)+[a-zA-Z]{2,3}\b")
    email_list = []

    #dates
    dates = [date(int(x[3]), int(x[2]), int(x[0])) for x in re.findall(r"\b(?:(0?[1-9]|[12][0-9]|3[01])(?P<deli>[\/\-\.])(0?[1-9]|1[012])(?P=deli)([0-9]{4}))\b", content)]
    dates.extend([date(int(x[0]), int(x[3]), int(x[2])) for x in re.findall(r"\b(?:([0-9]{4})(?P<deli>[\/\-\.])(0?[1-9]|[12][0-9]|3[01])(?P=deli)(0?[1-9]|1[012]))\b", content)])

    #sentences ....
    sentences = re.compile(r"[\.!?\n]+")
    sentence_count = 0

    for b in pat.findall(content):
        b = pat2.sub("", b).strip()

        sentence_count += len(sentences.findall(b))

        for float in floats.findall(b):
            float_list.append(float)

        for number in numbers.findall(b):
            number_list.append(number)

        for abv in abbreviations.findall(b):
            abbreviation_list.append(abv)

    for email in emails.findall(content):
        email_list.append(email)


    abbreviation_list = set(abbreviation_list)
    float_list = set(float_list)
    number_list = set(number_list)
    email_list = set(email_list)
    dates = set(dates)

#    pp.pprint(email_list)


    fp.close()
    print("filename:", filepath)
    print("author:", meta_tags['AUTOR'])
    print("keywords:", keywords)
    print("number of sentences:", sentence_count)
    print("number of abbreviations:", abbreviation_list.__len__())
    print("number of integer numbers:", number_list.__len__())
    print("number of float number:", float_list.__len__())
    print("number of dates:", dates.__len__())
    print("number of email addresses:", email_list.__len__())
    print("\n")


try:
    path = sys.argv[1]
except IndexError:
    print("Catalogue name is missing")
    sys.exit(0)

tree = os.walk(path)

for root, dirs, files in tree:
    for f in files:
        if f.endswith(".html"):
            filepath = os.path.join(root, f)
            processFile(filepath)
