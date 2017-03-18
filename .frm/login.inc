<form action="<?= PathUtils::getLink("/Login") ?>" method="post">
    <div class="form-group">
        <label for="loginUsername">Username:</label>
        <input type="text" class="form-control" id="loginUsername" name="loginUsername" placeholder="Username">
    </div>
    <div class="form-group">
        <label for="loginPassword">Password:</label>
        <input type="password" class="form-control" id="loginPassword" name="loginPassword" placeholder="Password">
    </div>
    <div class="form-group">
        <button type="submit" class="btn btn-primary">Login</button>
    </div>
</form>
