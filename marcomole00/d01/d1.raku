say 'input'.IO.split("\n\n").map(*.words.sum).sort(-*)[0,^3].map(*.sum);