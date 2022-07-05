each AiState has its own decision tree

each state has 3 parts of its frame cycle:
    observe: use game state to determine if we should change the state or remain unchanged
    think: traverse the decision tree for an action
    action: perform action (do nothing is an action)

if there's a processing overhead running all of these parts in one frame, we could break the state
cycle into 3 frames per cycle

----------
<wandering>
OBSERVE:
    target in line of sight?
      yes-> <stalking>
      no -> <wandering>

THINK:
 n1: has destination?
      yes-> n2
      no -> [new destination]
 n2: reached destination?
      yes-> [clear destination]
      no -> n3
 n3: stuck timeout > 3 sec?
      yes-> [clear destination]
      no -> [do nothing]

ACTION:
    do [action]
----------
<stalking>
OBSERVE:
    target in line of sight? (update path to target)
      yes-> <stalking>
      no -> <returning>

THINK:
 n1: close to target?
      yes-> [attack target]
      no -> n2
 n2: stuck timeout > 3 sec?
      yes-> [new path to target]
      no -> [do nothing]

ACTION:
    do [action]
----------
<returning>
OBSERVE:
    at return_dest?
      yes-> <wandering>
      no -> target in line of sight?
              yes-> <stalking>
              no -> <returning>

THINK:
 n1: has path to return_dest?
      yes-> n2
      no -> [create path to return_dest]
 n2: not moving > 3 sec?
      yes-> [new path to return_dest]
      no -> [do nothing]

ACTION:
    do [action]
----------
