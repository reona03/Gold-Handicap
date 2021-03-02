# Golf-Handicap
Intermediate Programming Using C/C++
For this project, you will be creating an application to calculate a simplified golf handicap. In order to keep
things simple, the score differential will be calculated based on a default par score of 72 and will NOT take into
account the course slope and rating.
The simplified handicap differential is calculated according to the following formula:
differential = score – 72
The handicap is then calculated using the average of the best (lowest) 10 differentials from the player’s past 20
total rounds, multiplied by 0.96. Any digits in the handicap after the tenths are truncated (not rounded).
Handicap = (sum of differentials / number of differentials) * 0.96
Note: Technically this calculation is the called handicap “index” but in our simplified version treat it as a simple
handicap.
If a golfer has scores for at least 5 but fewer than 20 rounds posted, the handicap is calculated using one to nine
differentials according to the schedule shown:




If the golfer has less than 5 rounds he does not have a handicap.
A golfer with a handicap less than 0 is considered a “scratch” golfer with a handicap of 0. There
are no negative handicaps.
For the purposes of this assignment you may limit the minimum score to 72.
The maximum handicap is 36.4.
You do not need to limit the maximum score but if you do it should not be less than 162.
