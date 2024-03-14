from subprocess import run, PIPE
import pytest

B_FILE_PATH = './bin/cafe'

def test_cafe_1():
    result = run([B_FILE_PATH], input='ORDER pizza\n500\nbeer\n200 BAR KITCHEN', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'beer\npizza\n'

def test_cafe_2():
    result = run([B_FILE_PATH], input='ORDER pizza\n500\nbeer\n200 ORDER soup\n300\ncola\n100 BAR BAR', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'beer\ncola\n'

def test_cafe_3():
    result = run([B_FILE_PATH], input='ORDER pizza\n500\nbeer\n200 KITCHEN STATS', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza\nKITCHEN 1 500\nBAR 0 0\n'

def test_cafe_4():
    result = run([B_FILE_PATH], input='STATS', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'KITCHEN 0 0\nBAR 0 0\n'

def test_cafe_5():
    result = run([B_FILE_PATH], input='CHECKOUT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'UNKNOWN COMMAND\n'

def test_cafe_6():
    result = run([B_FILE_PATH], input='ORDER pizza chips burger\n1500\ncola cola whiskey\n600 KITCHEN BAR STATS', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza chips burger\ncola cola whiskey\nKITCHEN 1 1500\nBAR 1 600\n'

def test_cafe_7():
    result = run([B_FILE_PATH], input='ORDER pizza\n1500\ncola\n100 ORDER pizza\n500\nwater\n0 ORDER pizza\n500\ncola\n500 KITCHEN KITCHEN KITCHEN BAR BAR BAR STATS', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza\npizza\npizza\ncola\nwater\ncola\nKITCHEN 3 2500\nBAR 3 600\n'

if __name__ == "__main__":
    pytest.main()