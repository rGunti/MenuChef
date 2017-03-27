# DriverLog &ndash; TODOs
This file contains a list of working items which should be done to either increase the
applications capabilities or to allow a specific feature to work, work better or more 
reliable.

- **Session Handler**<br>
PHP's default Session Handler is in use which is fine. But the application's framework should
get more control over the currently running sessions. An admin should be able to terminate
session from within the application. Also user modifications should be applied directly. This 
may result in higher database traffic but we gain more control over a sessions life cycle.

- **Exclude Configuration File from VCS**<br>
Currently the Application's Configuration is realized through a class with constants. While this
works quite well, it makes working with and updating VCS (in this case: git) unpleasant. We may
want to exclude it to a separate config file in a data directory (_Has PHP built in support for 
INI, XML, JSON or any suitable config file format?_). The file will be automatically created on
the first request and the defaults will be filled in. While this might work for minor things, 
the first request may result in a fatal crash. This could also be handled with an installer
script which helps creating the config file initially.
Also, a Config Documentation should be added to help explain the Config values.

- **Notification System**<br>
Implemented and working, although in some cases notifications are kept over one (1) page load 
and disappears afterwards.
<br>*This system should allow the developer to issue a notification during Request processing
and let it render on the UI. This can be Success Messages like "Logged In" or "Item saved",
Warnings or Errors like "Invalid credentials" or "User Account blocked".<br>
These notifications should be dismissible (maybe even auto-dismissing after _x_ seconds)
and contain a Title, Body and a Level of Severity (Info, Warning, Error).*

- **Data Listing**<br>
A system that allows data to be retrieved via AJAX and be displayed on-screen. 
[DataTables.js](https://datatables.net/) should be a good foundation for this and has 
previously been used in (non-public) projects like _Momoka Web Interface_.
**Update**: The user list uses this technique now. In the future, this could maybe be abstracted
so we don't have to write such a big chunck of code. But we might want to delay this for a while.
