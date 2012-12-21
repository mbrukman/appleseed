
#
# Copyright (c) 2012 Jonathan Topf
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#


import maya.cmds as cmds
import maya.OpenMaya as OpenMaya
import ms_commands
import os

SCRIPT_VERSION = '0.1.3'

def export(object_name, file_path, overwrite=True):
    if os.path.exists(file_path) and not overwrite:
        return

    export_dir = os.path.split(file_path)[0]

    if not os.path.exists(export_dir):
        os.makedirs(export_dir)

    # Open file for writing, overwriting previous contents.
    try:
        file_object = open(file_path, 'w')
    except IOError:
        error_msg = "IO error: failed to open {0} for writing.".format(file_path)
        cmds.error(error_msg)
        raise RuntimeError(error_msg)

    file_object.write("# File generated by ms_export_obj (Python) version {0}\n".format(SCRIPT_VERSION))

    sel = OpenMaya.MSelectionList()
    sel.add(str(object_name))

    mesh_dag_path = OpenMaya.MDagPath()
    sel.getDagPath(0, mesh_dag_path)
    
    mesh = OpenMaya.MFnMesh(mesh_dag_path)

    # Write vertices.
    points = OpenMaya.MPointArray() 
    mesh.getPoints(points)
    for i in range(points.length()):
        file_object.write("v {0} {1} {2}\n".format(points[i].x, points[i].y, points[i].z))
    
    # Write UV coordinates.
    us = OpenMaya.MFloatArray()
    vs = OpenMaya.MFloatArray()
    mesh.getUVs(us, vs)
    for i in range(us.length()):
        file_object.write("vt {0} {1}\n".format(us[i], vs[i]))

    # Write normals.
    normals = OpenMaya.MFloatVectorArray()
    mesh.getNormals(normals, 2) # 2 = object space
    for i in range(normals.length()):
        file_object.write("vn {0} {1} {2}\n".format(normals[i].x, normals[i].y, normals[i].z))

    # Write faces.
    poly_it = OpenMaya.MItMeshPolygon(mesh.object())
    while not poly_it.isDone():
        file_object.write("f")

        for i in range(poly_it.polygonVertexCount()):
            file_object.write(" {0}".format(poly_it.vertexIndex(i) + 1))

            if us.length() > 0 or normals.length() > 0:
                file_object.write("/")

            if us.length() > 0:
                # To get uv index we need to create an int pointer because the API is just wrappers for C++.
                util = OpenMaya.MScriptUtil()
                util.createFromInt(0)
                uv_pInt = util.asIntPtr()
                uv_index = OpenMaya.MScriptUtil()
                uv_index.createFromInt(0)
                poly_it.getUVIndex(i, uv_pInt)
                file_object.write("{0}".format(uv_index.getInt(uv_pInt) + 1))

            if normals.length() > 0:
                file_object.write("/{0}".format(poly_it.normalIndex(i) + 1))

        file_object.write("\n")
        poly_it.next()

    file_object.close()