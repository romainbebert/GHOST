#!/usr/bin/ruby

def usage
  puts  "Usage: " + $0 + " FILE"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

file = File.open(ARGV[0])

total = 0
wins = 0
draws = 0
live = 0
live_e = 0
hp = 0
hp_e = 0
me = false
currTurn = 0
endTurn = 0

tours = Array.new(150,0);
count = Array.new(150,0);

# For each line in file
file.each do |line|
  if line.include? "#"
    next
  end
  if line.include? "Draw"
    draws += 1
    total += 1
    next
  end

  words = line.split(': ')
  if words[0].include? "Winner"
    if words[1].include? "You"
      wins += 1
      me = true
    else
      me = false
    end
    endTurn += currTurn
    total += 1
  elsif words[0].include? "Diff"
    if words[1].to_i > 0
      live += words[1].to_i
    elsif words[1].to_i < 0
      live_e += words[1].to_i
    end
  elsif words[0].include? "Turn"
    currTurn = words[1].to_i
  elsif words[0].include? "Total Damage"
    tours[currTurn] = tours[currTurn] + words[1].to_f
    count[currTurn] = count[currTurn] + 1
  elsif words[0].include? "HP"
    if me
      hp += words[1].to_f
    else
      hp_e += words[1].to_f      
    end
  end
end

mean_live = (live.to_f / wins).round(1)
mean_hp = (hp / wins).round(1)
mean_live_e = (-live_e.to_f / ( total - wins - draws ) ).round(1)
mean_hp_e = (hp_e / ( total - wins - draws ) ).round(1)
percent = (100 * wins.to_f / total).round(1)


puts "#{ARGV[0]}:\n   #{percent}\% of wins (#{wins}/#{total}, #{draws} draws)"
puts "   Average number of GHOST living units = #{mean_live}"
puts "   Average number of enemy living units = #{mean_live_e}"
puts "   Average GHOST HP = #{mean_hp}"
puts "   Average enemy HP = #{mean_hp_e}"
puts "   Average number of turns = #{endTurn/total}"
puts "Average damages per turn"
tours.each_index { |index|   
  #puts index
  #puts tours[index] 
  #puts count[index]
  puts count[index] == 0 ? tours[index] : tours[index] > 1000000000 ? "error when computing damages" : (tours[index]/count[index]) 
}

exit