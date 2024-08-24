"use client";

import { api } from "~/trpc/react";

export function PostList() {
  const posts = api.post.all.useQuery();

  return (
    <div>
      <h1>Posts</h1>
      {posts.isLoading ? (
        <p>Loading posts...</p>
      ) : posts.error ? (
        <p>Error loading posts: {posts.error.message}</p>
      ) : posts?.data?.length === 0 ? (
        <p>No posts found.</p>
      ) : (
        <ul>
          {posts?.data?.map((post) => (
            <li key={post.id}>
              <p>{post.text}</p>
              <p>Posted by: {post.user.handle}</p>
            </li>
          ))}
        </ul>
      )}
    </div>
  );
}
