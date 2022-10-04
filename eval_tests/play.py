import subprocess
import sys

# Usage: "python play.py total_games map_name"
#
# Set players here.
p1 = "../resources/players/superjeannot.filler"
p2 = "../swilliam.filler"
map_input = str(sys.argv[2])
map = "../resources/maps/"+map_input

p1_score = 0
p2_score = 0
draw = 0
i = 0
rounds = int(sys.argv[1])
if rounds > 1:
    round_str = "rounds"
else:
    round_str = "round"
endmessage = "\nSuccessfully completed "+str(rounds)+" "+round_str+"!"

while (i < rounds):
    ret = subprocess.call(["../resources/filler_vm", "-p1", p1, "-p2", p2, "-f", map, "-q"])
    p1_score += ret == 1
    p2_score += ret == 2
    draw += ret == 0
    i += 1

p1 = p1.replace("resources/players/", "")
p1 = p1.replace("../", "")
p1 = p1.replace(".filler", "")
p2 = p2.replace("resources/players/", "")
p2 = p2.replace("../", "")
p2 = p2.replace(".filler", "")
print("________________________________________________")
print(endmessage)
print("Player 1 = ", p1_score, p1)
print("Player 2 = ", p2_score, p2)
print("Draws    = ", draw)
