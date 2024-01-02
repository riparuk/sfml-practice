## things that need to be considered

### Itrator Invalidation
occurs when an iterator to an element in a data structure such as an array, list, or map is no longer valid or reliable due to a change in the data structure (removal of an element or addition in the array, list, or map).

Example in C++
```cpp
// Function to handle collisions between bullets and tiles
void HandleCollisions() {
    EntityVec bullets;  // Vector of bullets
    EntityVec tiles;    // Vector of tiles

    // Iterate over bullets
    for (auto itBullet = bullets.begin(); itBullet != bullets.end(); ++itBullet) {
        // Iterate over tiles
        for (auto itTile = tiles.begin(); itTile != tiles.end(); ++itTile) {
            // Check for collision using the Physics::IsCollision function
            if (Physics::IsCollision(*itBullet, *itTile)) {
                // Potential iterator invalidation issue here
                bullets.erase(itBullet);
                // After erasing an element, itBullet may be invalidated
                // and cannot be reliably used anymore
                // It may point to the end() or an arbitrary position in the vector
            }
        }
    }
}
```
