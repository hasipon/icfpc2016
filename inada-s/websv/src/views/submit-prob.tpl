% include('head.tpl')

<div class="container">

<h1>Update Problem for {{params['publish_time']}}</h1>

<form>
  <div class="form-group">
    <label>solution</label>
    <textarea class="form-control" name="solution" rows="20" required></textarea>
  </div>
  <button type="submit" class="btn btn-success" formaction="/submit-problem/{{params['publish_time']}}" formmethod="POST">Submit</button>
</form>

</div>

% include('tail.tpl')
