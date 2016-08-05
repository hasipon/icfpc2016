import json
import glob
import os
import subprocess
from bottle import route, template, request, static_file, redirect, auth_basic, error, response, get, abort, run, debug

repo = '/home/ubuntu/inada-s/websv'
www = repo + '/inada-s/websv/www'
src = repo + '/inada-s/websv/src'
solutions = repo + '/solutions'
problems = repo + '/problems'

"""
Static Routing
"""
@route('/img/<file_name>')
def img(file_name):
    return static_file(file_name, root=www+'/img')

@route('/problems/<file_name>')
def route_problems(file_name):
    return static_file(file_name, problems)

@route('/css/<file_name>')
def css(file_name):
    return static_file(file_name, root=www+'/css')

@route('/js/<file_name>')
def js(file_name):
    return static_file(file_name, root=www+'/js')

@route('/fonts/<file_name>')
def fonts(file_name):
    return static_file(file_name, root=www+'/fonts')

def find_best_solutions():
    ret = {}
    sol = glob.glob(solutions + "/*.txt")
    for s in sol:
        base_name, _ = os.path.splitext(os.path.basename(s))
        pid, shash = base_name.split('-')
        pid = int(pid)
        tmp, _ = os.path.splitext(s)
        json_data = open(tmp + ".json").read()
        data = json.loads(json_data)
        if not data["ok"]:
            continue
        if pid in ret:
            if ret[pid]['json']['resemblance'] > data['resemblance']:
                continue
        ret[pid] = dict(json=data, solution_path=s)
    return ret


"""
Public Page Routing
"""
@route('/')
def title():
    json_data = open(repo + "/problems.json").read()
    data = json.loads(json_data)
    probs = data['problems']
    sol = find_best_solutions()
    for p in probs:
        p['solution_path'] = ""
        p['ok'] = False
        pid = p['problem_id']
        if pid in sol:
            p['ok'] = True
            p['solution_path'] = sol[pid]['solution_path']
            p['soljson'] = sol[pid]['json']
            myrank = 1
            res = sol[pid]['json']['resemblance']
            size = sol[pid]['json']['solution_size']
            for i in xrange(len(p['ranking'])):
                if p['ranking'][i]['resemblance'] > res or (p['ranking'][i]['resemblance'] == res and p['ranking'][i]['solution_size'] < size):
                    myrank += 1
                else:
                    break
            p['rank'] = myrank
    return template('problems', problems=probs)

@route('/dbg')
def dbg():
    return find_best_solutions()

@route('/pull')
def pull():
    output = subprocess.check_output(["git", "pull", "origin", "master"])
    return "<pre>" + output + "</pre>"

debug(True)
run(host="0.0.0.0", port=8000)
