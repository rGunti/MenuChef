# DriverLog
DriverLog is a PHP web application aiming to log your personal driving history.

The goal of this project is that the user is able to record the trips they made and the money 
they spent on fuel. This recorded data can than be used to calculate a gas mileage as well as
cost per distance and for general recording purposes.

## Features
_pending_

### Localization
The framework of this projects supports localization. You can add your own language by copying one of
the `*.inc` files in the [.l10n](.l10n) folder and translating its content to your language. These
files also feature a "header" with information about the translated language like:

- Language Name
- Author
- Country Flag (you can find a collection of Flag icons in the [img/lang](img/lang) folder)

The language used for every user is guessed by parsing the information the web browser transmits.
If any of the requested languages are available, they will be used by default. If none is available
the default will be used, which is English in this case. If you want to change this behaviour you
can edit the constant `L10N::L10N_DEFAULT` found in [.src/l10n.inc](.src/l10n.inc).

The user is able to change their desired language via a language menu at the top right corner of
the screen. A list with all available languages will be presented to them to choose from.
If you have a cookie editor plugin installed look for the cookie `ForcedLanguage`.

### Styles
At the moment, there are multiple Bootstrap styles integrated in the application but the user is
not able to select a specific one via the GUI (yet). You can force your browser to use a different
style by using a cookie editor plugin and adding a cookie named `UsedTheme`. The following themes
are available at this time:
- [default](css/bootstrap.min.css) (_acutally not the default but named like this because it is 
Bootstrap without any additional themes_)
- [defaulttheme](css/bootstrap-theme.min.css) (_Bootstraps default theme_)
- [darkmode](css/bootswatch.min.css) (this is the **Default** Theme)
- [darkadmin](css/darkadmin.min.css)
- [superhero](css/superhero.min.css)

It is planned to add a menu which allows the user to change the theme on the fly. It should also
be possible to save the users favorite theme not only as a cookie but also in their profile so
it does not have to be selected each time. But this feature is low in priority.

## Used Technologies and Libraries
- Apache Web Server with **PHP 5.6**
- [Bootstrap](http://getbootstrap.com) 3.7
- MySQL  (_though another DBMS could theoretically be used instead_)
- [jQuery](http://jquery.com) 1.12.4
- [DataTables](https://datatables.net/) 1.10.13
- ...

## Roadmap
This projects builds upon a self-build "Framework" which can (and should) be used in later (own)
projects. "DriverLog" serves as a test project for this Framework which then later can be used to 
write more web applications.

The core of this framework is a unified, object-oriented request handling with easy database access
and [DataTables](https://datatables.net/) as its core for displaying data on the GUI.

## Setup
_This project is not in a working state right now so you cannot use it right now._
1. Create a schema on your MySQL Server.
2. Run [.db/DbInit.sql](.db/DbInit.sql)
3. Copy the whole content of this repository to your Web Server. Make sure `Override` is allowed
in your servers config and `mod_rewrite` is installed and enabled as well.
4. Configure the web application using the [.cfg/config.inc](.cfg/config.inc). Set the correct
Database Server credentials.
5. If you want to use Logging, create a directory of Logging (e.g. `C:\TEMP` on Windows) 
and make sure Apache has write access to this folder. Change the path
in the config file while using `%date%` as a placeholder for the current date 
(`driverlog.%date%.log` => `driverlog.2017-03-23.log`).
6. If everything is setup correctly, you can access the application and login with the default 
user accounts.

## Default Login Credentials
| Username | Password | Permission Level   |
| -------- | -------- | ------------------ |
| admin    | admin    | Administrator      |

### Regarding Permission Levels
The application knows the following permission levels:
- Logged Out User
- Normal User
- Administrator

## Notes about "Productive" Systems
You may want to remove the following files and folders from a productive environment:
- `.db` folder
- `*.md` files
- `.git*` files

Every dot-prefixed sub-folder contains a special `.htaccess` file which strictly denies 
any access to the directory. Only PHP should be able to access these folders to include source code.
All files which are not meant to be executed standalone use the file extension `.inc`. These cannot
be executed by calling them in a browser but they will present themselves as text files which might
reveal your configuration files. 

Please check if you are able to access e.g. the `.cfg/config.inc` file from your Web Browser. 
If so, check your web servers manual on how to protect these directories. If you get a 403 Error then
you are good to go.

## License
This Project is licensed under the **MIT License**.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

More information in the dedicated [LICENSE file](LICENSE).

## TODOs
- listed [here](TODOs.md)
