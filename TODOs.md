# DriverLog &ndash; TODOs
This file contains a list of working items which should be done to either increase the
applications capabilities or to allow a specific feature to work, work better or more 
reliable.

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

- **Extend PDO Methods**<br>
The currently available PDO methods (found in [.src/db.inc](.src/db.inc)) are not
enough. We need Inserts, Updates and Deletes as well as Transactional Support. Most of these
functions can be taken from _Momoka Web Interface_ although they have to be rewritten to match
this projects coding style.
