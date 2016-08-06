% include('head.tpl')

<div class="container">
<h1>Challenges</h1>

<table class="table table-condensed table-striped">
<tr>
    <th class="text-center">id</th>
    <th class="text-center">publish_time</th>
    <th class="text-center">problem_id</th>
    <th class="text-center">problem_size</th>
    <th class="text-center">problem_spec_hash</th>
    <th class="text-center">solution_size</th>
    <th class="text-center">solution_spec_hash</th>
    <th class="text-center">update</th>
</tr>

% for i in xrange(1470441600, 1470603601, 3600):

% ok = i in params
% if ok:
<tr class="info">
% else:
<tr>
% end
    <td class="text-center">{{(i - 1470441600) / 3600 + 1}}</td>
    <td class="text-center">{{i}}</td>
% if ok:
    <td class="text-center"> {{params[i]['problem_id']}} </td>
    <td class="text-center"> {{params[i]['problem_size']}} </td>
    <td class="text-center"> {{params[i]['problem_spec_hash']}} </td>
    <td class="text-center"> {{params[i]['solution_size']}} </td>
    <td class="text-center"> {{params[i]['solution_spec_hash']}} </td>
% else:
    <td class="text-center"></td>
    <td class="text-center"></td>
    <td class="text-center"></td>
    <td class="text-center"></td>
    <td class="text-center"></td>
% end
    <td class="text-center"><a href="/submit-problem/{{i}}"><span class="glyphicon glyphicon-upload" aria-hidden="true"></span></a></td>
</tr>
% end

