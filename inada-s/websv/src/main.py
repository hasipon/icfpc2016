import json
import time
import glob
import os
import subprocess
from bottle import route, template, request, static_file, redirect, auth_basic, error, response, get, abort, run, debug

repo = '/home/ubuntu/inada-s/websv'
www = repo + '/inada-s/websv/www'
src = repo + '/inada-s/websv/src'
solutions = repo + '/solutions'
problems = repo + '/problems'
challenges = repo + '/challenges'
visualizer = repo + '/sawa/visualizer/bin'

"""
Static Routing
"""
@route('/img/<file_name>')
def img(file_name):
    return static_file(file_name, root=www+'/img')

@route('/problems/<file_name>')
def route_problems(file_name):
    return static_file(file_name, problems)

@route('/visualizer/<file_name>')
def route_problems(file_name):
    return static_file(file_name, visualizer)

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

def make_user_dict(json_data):
    users = json_data['users']
    leaderboard = json_data['leaderboard']
    ret = {}
    for u in users:
        print u
        ret[u['username']] = u
    for u in leaderboard:
        ret[u['username']]['score'] = u['score']
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
    users = make_user_dict(data)
    for p in probs:
        p['solution_path'] = ""
        p['ok'] = False
        if p['owner'] in users:
            p['owner'] = users[p['owner']]['display_name'] + '(' + p['owner']  + ')'
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
    return template('output', output=output)

@route('/submit-solution')
def solution_submit_get():
    return template('submit')

@route('/submit-solution', method='POST')
def solution_submit_post():
    problem_id = request.forms.get('problem_id')
    solution = request.forms.get('solution')
    solution.replace('\r\n','\n')
    filename = "/tmp/" + problem_id + "-" + str(time.time())
    with open(filename, 'w') as f:
        f.write(solution)
    output = subprocess.check_output([repo + "/solution-submit", problem_id, filename])
    os.remove(filename)
    return template('output', output=output)

@route('/gitstatus')
def git_status():
    output = ""
    try:
        output += subprocess.check_output(["git", "status"])
    except subprocess.CalledProcessError, e:
        output += "Error:" + e.output
    return template('output', output=output)

@route('/pushsolution')
def push_solution():
    output = ""
    try:
        output += subprocess.check_output(["git", "pull", "origin", "master"])
        output += subprocess.check_output(["git", "add", solutions])
        output += subprocess.check_output(["git", "commit", "-m", "update solution from webserver"])
        output += subprocess.check_output(["git", "push", "origin", "master"])
    except subprocess.CalledProcessError, e:
        output += "Error:" + e.output
    return template('output', output=output)

@route('/pushchallenge')
def push_solution():
    output = ""
    try:
        output += subprocess.check_output(["git", "pull", "origin", "master"])
        output += subprocess.check_output(["git", "add", challenges])
        output += subprocess.check_output(["git", "commit", "-m", "update challenges from webserver"])
        output += subprocess.check_output(["git", "push", "origin", "master"])
    except subprocess.CalledProcessError, e:
        output += "Error:" + e.output
    return template('output', output=output)

@route('/challenges')
def route_challenges():
    files = glob.glob(challenges + "/*.json")
    params = {}
    for f in files:
        data = json.loads(open(f).read())
        params[data["publish_time"]] = data
    return template('challenges', params=params, files=files, path=challenges + "/*.json")

@route('/submit-problem/<publish_time:int>')
def problem_submit_get(publish_time):
    params = {}
    params["publish_time"] = publish_time
    return template('submit-prob', params=params)

@route('/submit-problem/<publish_time>', method='POST')
def problem_submit_post(publish_time):
    solution = request.forms.get('solution')
    solution.replace('\r\n','\n')
    filename = "/tmp/" + publish_time + "-" + str(time.time())
    with open(filename, 'w') as f:
        f.write(solution)
    output = subprocess.check_output([repo + "/problem-submit", publish_time, filename])
    os.remove(filename)
    return template('output', output=output)

debug(True)
run(host="0.0.0.0", port=8000)
