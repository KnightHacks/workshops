"use client";

import { api } from "~/trpc/react";
import { Post } from "./post";

export function PostList({ userId }: { userId: string }) {
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
            <Post key={post.id} post={post} userId={userId} />
          ))}
        </ul>
      )}
    </div>
  );
}
