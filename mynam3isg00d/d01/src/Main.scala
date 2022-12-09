import scala.io.Source

@main
def d01(): Unit = {
  val nl = System.lineSeparator
  val sol = Source.fromFile("mynam3isg00d/d01/input.txt")
                    .mkString
                    .split(nl+nl)
                    .map(s => {
                      s.split(nl).map(f => f.toInt).sum
                    }).sorted.reverse.take(3)
  
  println("Part 1: " + sol.head)
  println("Part 2: " + sol.sum)
}