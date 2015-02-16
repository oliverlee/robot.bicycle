#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Output controller gains to .cc and .h files.
#
# To run: ./generate_cgains.py
#

import os
import sys
import jinja2
import yaw_rate_controller as yrc

def generate(ccinfile, hinfile):
    c_data = yrc.design_controller()
    c_data_sorted = sorted(c_data, key=lambda c: c['theta_R_dot'])
    render_dict = {'NUMGAINS' : len(c_data_sorted),
                   'STATESIZE' : 4,
                   'INPUTSIZE' : 3,
                   'OUTPUTSIZE' : 1}
    SPEED = []
    A = []
    B = []
    C = []
    KP = []
    KI = []
    for i in range(render_dict['NUMGAINS']):
        SPEED.append(c_data_sorted[i]['theta_R_dot'])
        KP.append(c_data_sorted[i]['Kp_fit'])
        KI.append(c_data_sorted[i]['Ki_fit'])
        A.append(c_data_sorted[i]['A_e'])
        B.append(c_data_sorted[i]['B_e'])
        C.append(c_data_sorted[i]['K_c'])
    render_dict['SPEED'] = SPEED
    render_dict['A'] = A
    render_dict['B'] = B
    render_dict['C'] = C
    render_dict['KP'] = KP
    render_dict['KI'] = KI
    generate_file(ccinfile, render_dict, '.cpp')
    generate_file(hinfile, render_dict, '.h')


def generate_file(filename, render_dict, extension):
    template = template_setup(filename)
    outfile = name_outfile(filename, extension)
    with open(outfile, 'w') as f:
        f.write(template.render(render_dict))

def template_setup(filename):
    dirname, basename = os.path.split(os.path.abspath(filename))
    env = jinja2.Environment(loader=jinja2.FileSystemLoader(dirname),
                             undefined=jinja2.StrictUndefined,
                             trim_blocks=True)
    return env.get_template(basename)

def name_outfile(infile, ext):
    dirname, basename = os.path.split(os.path.abspath(infile))
    base0, ext0 = os.path.splitext(basename)
    base1, ext1 = os.path.splitext(base0)
    if ext0 == '.in' and ext1 == ext:
        return os.path.join(dirname, base0)
    if ext0 == ext:
        return os.path.join(dirname, base0 + '_gen' + ext0)
    return os.path.join(dirname, basename + '_gen' + ext)


if __name__ == '__main__':
    generate('../firmware/src/fork_schedule.cpp.in',
             '../firmware/src/gain_schedule.h.in');
    sys.exit(0)
