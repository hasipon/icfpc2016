% include('head.tpl')

<div class="container">

<h1>Submit</h1>

<form>
  <div class="form-group">
    <label>problem_id</label>
    <input type="text" class="form-control" name="problem_id" maxlength="5" required>
  </div>
  <div class="form-group">
    <label>solution</label>
    <textarea class="form-control" name="solution" rows="20" required></textarea>
  </div>
  <button type="submit" class="btn btn-success" formaction="/submit-solution" formmethod="POST">Submit</button>
</form>

</div>

% include('tail.tpl')
