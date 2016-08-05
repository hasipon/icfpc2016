% include('head.tpl')

<div class="container">

<h1>Problems</h1>

<table class="table table-condensed table-striped">
<tr>
    <th class="text-center">problem_id</th>
    <th class="text-center">ranking</th>
    <th class="text-center">resemblance</th>
    <th class="text-center">solution_size</th>
    <th class="text-center">problem_size</th>
    <th class="text-center">solution_size</th>
    <th class="text-center">official</th>
</tr>
% for p in problems:

% if p['ok']:
% if p['soljson']['resemblance'] == 1:
<tr class="success">
% elif p['soljson']['resemblance'] != 0:
<tr class="info">
% else:
<tr>
% end
% end
    <td class="text-center">
    <a href="/problems/{{p['problem_id']}}.png">{{p['problem_id']}}</a>
    </td>

    <td class="text-center">
% if p['ok']:
    {{p['rank']}} / {{len(p['ranking'])}}
% end
    </td>
    <td class="text-center">
% if p['ok']:
  {{p['soljson']['resemblance']}}
% end
    </td>
    <td class="text-center">
% if p['ok']:
  {{p['soljson']['solution_size']}}
% end
    </td>
    <td class="text-center">{{p['problem_size']}}</td>
    <td class="text-center">{{p['solution_size']}}</td>

    <td class="text-center">
    <a href="http://2016sv.icfpcontest.org/problem/view/{{p['problem_id']}}">detail</a>
    </td>
</tr>
% end

</div>

% include('tail.tpl')

