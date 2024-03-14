from subprocess import run, PIPE
import pytest

B_FILE_PATH = './bin/air_traffic'

def test_air_traffic_1():
    result = run([B_FILE_PATH], input='4000 8000 4', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'SAFELY'

def test_air_traffic_2():
    result = run([B_FILE_PATH], input='4000 5000 5', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'DANGEROUS\a'

def test_air_traffic_3():
    result = run([B_FILE_PATH], input='7000 7600 3', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'SAFELY'

def test_air_traffic_4():
    result = run([B_FILE_PATH], input='7000 7899 4', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'DANGEROUS\a'

def test_air_traffic_5():
    result = run([B_FILE_PATH], input='7000 7000 1', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'SAFELY'

if __name__ == "__main__":
    pytest.main()