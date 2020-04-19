with open("ans.txt") as f:
  count = 1
  ans = ""
  curr = ""
  while True:
    c = f.read(1)
    if not c:
      print("End of file")
      break
    if count == 256:
      ans += curr + c + "\n"
      curr = ""
      count = 1
    else: 
      curr += c + ","
      count += 1
  text_file = open("test.dat", "w")
  n = text_file.write(ans)
  text_file.close()