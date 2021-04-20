# Python - Virtual Environments

Python's virtual environment allow to set up an environment that meets the
requirements to run a Python application.

From the official documentation at https://docs.python.org/3/tutorial/venv.html:

  [...] a virtual environment, a self-contained directory tree that contains a
  Python installation for a particular version of Python, plus a number of
  additional packages.

## Creating Virtual Environments

```
python3 -m venv <dir_name>
```

**Note:** Python 2 uses `virtualenv <dir_name>`

## Activate/Deactivate Virtual Environment

```
source <dir_name>/bin/activate
```

After sourcing, just type `deactivate` to leave the virtual environment.

## Managing Packages with pip

```
pip search
pip install
pip freeze > requirements.txt
pip install -r requirements.txt
```

## Managing Virtual Environments

```
pip install virtualenvwrapper
```

`virtualenvwrapper` offers following commands:

```
workon
deactivate
mkvirtualenv
cdvirtualenv
rmvirtualenv
```

**Tip:** add following lines to `.bashrc`

```
export WORKON_HOME=$HOME/.virtualenvs   # Optional
export PROJECT_HOME=$HOME/projects      # Optional
source /usr/local/bin/virtualenvwrapper.sh
```
