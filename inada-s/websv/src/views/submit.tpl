% include('head.tpl')

<div class="container">

<h1>提出</h1>

<form>
  <div class="form-group">
    <label for="user_name">問題ID</label>
    <input type="text" class="form-control" name="problem_id" maxlength="5" required>
  </div>
  <div class="form-group">
    <label for="user_post">回答</label>
    <textarea class="form-control" name="solution" cols="50" rows="10" required></textarea>
  </div>
  <button type="submit" class="btn btn-success" formaction="/submit-solution" formmethod="POST">Submit</button>
</form>

</div>

% include('tail.tpl')
