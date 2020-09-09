require "minitest/autorun"
require_relative "../lib/lab1"

class Lab1Test < Minitest::Test

#  def test_that_it_has_a_version_number
#    refute_nil ::Lab1::VERSION
#  end
  def test_kek
    assert true
  end
  def test_setup
    @matrix = Matrix.new
  end

  def test_size
    m = Matrix.new
    assert @matrix.n == 10
  end
end
