import subprocess
import sys
import os

class colour:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'


print(colour.UNDERLINE + \
    "                                                "+ colour.END)
print(colour.UNDERLINE + \
    "                    FILLER                      "+ colour.END)

# List of opponents to choose from
opponent_list = os.listdir('./resources/players/')
opponents = ", ".join(map(str, opponent_list))
opponents = opponents.replace(".filler", "")

# List of maps to choose from
map_list = os.listdir('./resources/maps/')
maps = ", ".join(map(str, map_list))
maps = maps.replace("map0", "")

# User inputs their chosen opponent
name = raw_input(colour.UNDERLINE \
        + "\nWhich opponent would you like to face?\n" \
        + colour.END +opponents+"\n> ")
# User inputs their chosen map
map_input = raw_input(colour.UNDERLINE \
        + "Which map would you like to play?\n" \
        + colour.END +maps+"\n> ")
# User inputs a custom number of rounds to play
rounds = int(input(colour.UNDERLINE \
        + "How many rounds would you like to play?" \
        + colour.END+ "\n> "))

print(colour.UNDERLINE + \
    "                                                "+ colour.END)
print(colour.UNDERLINE + \
    "                    FILLER                      "+ colour.END)
print("")

# Set as your executable name
you = "swilliam.filler"

# Game data. Simply reverse p1 and p2 to play as player one or two.
p1 = "./resources/players/"+name+".filler"
p2 = "./"+ you
map = "./resources/maps/map0"+map_input
round_str = "rounds" if rounds > 1 else "round"
endmessage = "Successfully completed "+str(rounds)+" "+round_str+"!"
centered_end = endmessage.center(48, ' ')

# Scores
p1_score = 0
p2_score = 0
draw = 0

# Game processing
i = 0
while (i < rounds):
    ret = subprocess.call(\
        ["./resources/filler_vm", "-p1", p1, "-p2", p2, "-f", map, "-q"])
    p1_score += ret == 1
    p2_score += ret == 2
    draw += ret == 0
    i += 1

# Remove directories from player names
p1 = p1.replace("resources/players/", "")
p1 = p1.replace("./", "")
p1 = p1.replace(".filler", "")
p2 = p2.replace("resources/players/", "")
p2 = p2.replace("./", "")
p2 = p2.replace(".filler", "")

# Final scoring
print(colour.UNDERLINE + \
    "                                                "+ colour.END)
print(colour.UNDERLINE + centered_end + colour.END + "\n")
print("(Player 1) "+ p1 +" scored: "+ str(p1_score))
print("(Player 2) "+ p2 +" scored: "+ str(p2_score))
if (draw > 0):
    print("Draws = "+ str(draw))
print("")