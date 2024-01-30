# default goal
all: target

# dep_a2 and dep_b2 depend on dep_a1 and dep_b1, therefore dep_a1 and dep_b1 must be created first
dep_a2: dep_a1
	cp dep_a1 dep_a2

dep_b2: dep_b1
	cp dep_b1 dep_b2

# target depends on dep_a2 and dep_b2, therefore they must be created first
target: dep_a2 dep_b2
	cat dep_a2 dep_b2 > target

# create dep_a1 and dep_b1
dep_a1:
	echo "dep_a1" > dep_a1

dep_b1:
	echo "dep_b1" > dep_b1

# run "make clean" to start from scratch
clean:
	rm -rf target dep_*