# This contains the notes that i keep to track things i need to fix or improve.

# Memory Leak !!!!

In this current design of the ECS system there is a memory leak in 
destructor of Archetype Manager where we only free archetype chunk as 
whole to which ever allocator we got but since our ECS components are not 
simple POD(Plain ol  Data) we need to call destructor of each components in the 
archetype chunk individually , this would require more complex destructor

The destructor currently is kept simple cause i intent to redesign the memory allocation and deallocation code.

# Bugs that cropped up during Testing

- Archetype Manager needs way to handle archetypeSignature with 
  zero set bits , this casued error when trying to access the component
  layouts in archetype definition for this zero signature.


# Design Issue to solve

A design problem that i overlooked was that in a archetypechunk the offset 
info where each component starts is stored in a vector and i have no way to 
get offset using component Id. Now i could use unordered map or map but i am 
thinking of a better way to do this.may be i should use unordered map or map 
itself casue the overhead is just per archetype.



# Redundancies Noted

I think we dont need archetype Definition in ArchetypeChunkHeader
instead use Archetype signature to get it from the signature to
defintion map in archetypeManager.


# Better performance optimizations

I could use unique pointers instead of making copies of stuff and returning it , my assumption is that compiler 
is smart enough to create objects in place but need to look into it 

# Inavlid IDs

Need to think about adding a invalid entity id and component id to express invalid entity or component.



# TODO IMPORTANT

1) Should 	`ComponentId ComponentRegistry::getComponentIdFromComponent() const` method in componentManager be const amd not allow creation of new component.


# Issue regarding ArchetypeChunkRecord struct
	struct ArchetypeRecordChunk
	{
		EntityId id[];

	};
  //The use of  alignof(ArchetypeRecordChunk) is little bad cause what if compiler inserts padding in ArchetypeChunkRecord struct
		void* ArchetypeRecordChunkRawPtr = _aligned_malloc(MAX_NUM_OF_ENTITIES_PER_CHUNK*sizeof(EntityId), alignof(ArchetypeRecordChunk));


  The fix is to change to 	
  
	struct ArchetypeRecordChunk
	{
		EntityId* id = nullptr;
	};

  and very importantly use 
  	void* ArchetypeRecordChunkRawPtr = _aligned_malloc(MAX_NUM_OF_ENTITIES_PER_CHUNK*sizeof(EntityId), alignof(EntityId));
    !!! DONT USE  alignof(ArchetypeRecordChunk));
