# Design Notes for AI behavior trees / models

Each AiState has its own decision tree

Each state has 3 steps to process in a single frame:
    observe: use game state to determine if we should change the state or remain unchanged
    think: traverse the decision tree for an action
    action: perform action (do nothing is an action)

## Notes 

if there's too much processing overhead running all of these parts in one frame, I could break the state cycle into 3 frames per cycle.

I'm also considering adding a "heartbeat" which will only process the behavior tree after a certain number of frames has passed to slow everything down a bit
    - this could mean the AI overshoots its destination, though...


## State: Wandering

### Step 1: OBSERVE
    target in line of sight?
        yes-> action=<change state: stalking>
        no -> action=<change state: wandering> or <do nothing>

### Step 2: THINK
    n1: has destination?
        yes-> n2
        no -> action=<get a new destination>
    n2: reached destination?
        yes-> action=<clear destination>
        no -> n3
    n3: stuck timeout > X sec?
        yes-> action=<clear destination>
        no -> action=<do nothing>

### Step 3: ACTION
    process <action>

## State: Stalking

### Step 1: OBSERVE
    target in line of sight? (update path to target)
        yes-> action=<change state: stalking> or <do nothing>
        no -> action=<change state: returning>

### Step 2: THINK
    n1: close to target?
        yes-> action=<attack target>
        no -> n2
    n2: stuck timeout > X sec?
        yes-> action=<generate a new path: target>
        no -> action=<do nothing>

### Step 3: ACTION
    process <action>


## State: Returning

### Step 1: OBSERVE
    at return_dest?
        yes-> action=<change state: wandering>
        no -> target in line of sight?
            yes-> action=<change state: stalking>
            no -> action=<change state: returning> or <do nothing>

### Step 2: THINK
    n1: has path to return_dest?
        yes-> n2
        no -> action=<create path to return_dest>
    n2: stuck timeout > X sec?
        yes-> action=<generate a new path: return_dest>
        no -> action=<do nothing>

### Step 3: ACTION
    process <action>
